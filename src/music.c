#include <stdio.h>
#include <string.h>

#define MAX_URL_LENGTH 2048
#define MAX_SONG_STRING_LENGTH 1024
#define MAX_SHELL_COMMAND_LENGTH 1024

typedef struct {
  char* title;
  char* album;
  char* artist;
  int id;

  char* url;

} Song;

static int shell_command_stdout(char* command) {

  FILE* pFile; // File stream.
  // Open pipe to shell command in read mode.
  pFile = popen(command, "r");

  // Error handling.
  if (pFile == NULL) { puts("Failed to open pipe."); return -1; }

  // While there are bytes to read, print to stdout.
  char buf[1024];
  while (fgets(buf, sizeof(buf), pFile)) fprintf(stdout, "%s", buf);

  // Close the pipe.
  pclose(pFile);

  return 0;
}

static int shell_command(char* command, char* buf) {

  FILE* pFile; // File stream.
  // Open pipe to shell command in read mode.
  pFile = popen(command, "r");

  // Error handling.
  if (pFile == NULL) { puts("Failed to open pipe."); return -1; }

  // Write output (one line) to buf.
  fgets(buf, MAX_URL_LENGTH, pFile);

  // Close the pipe.
  pclose(pFile);

  return 0;
}

int download_song(char* url) {

  char command[MAX_URL_LENGTH];
  sprintf(command, "yt-dlp -o \"./music/%%(title)s.%%(ext)s\" --extract-audio %s", url);

  shell_command_stdout(command);
}

int get_title(char* url, char* buf) {

  // Set up shell command.
  char command[MAX_SHELL_COMMAND_LENGTH];
  sprintf(command, "yt-dlp --quiet --no-warnings --print \"%%(title)s\" %s", url);

  // Execute shell command.
  return shell_command(command, buf);
}

int get_album(char* url, char* buf) {
  // Set up shell command.
  char command[MAX_SHELL_COMMAND_LENGTH];
  sprintf(command, "yt-dlp --quiet --no-warnings --print \"%%(album)s\" %s", url);

  // Execute shell command.
  return shell_command(command, buf);
}

int get_artist(char* url, char* buf) {
  // Set up shell command.
  char command[MAX_SHELL_COMMAND_LENGTH];
  sprintf(command, "yt-dlp --quiet --no-warnings --print \"%%(channel)s\" %s", url);

  // Execute shell command.
  return shell_command(command, buf);
}

int get_id(char* url, char* buf) {
  // Set up shell command.
  char command[MAX_SHELL_COMMAND_LENGTH];
  sprintf(command, "yt-dlp --quiet --no-warnings --print \"%%(id)s\" %s", url);

  // Execute shell command.
  return shell_command(command, buf);
}

Song get_song_info(char* url) {
  char title  [MAX_SONG_STRING_LENGTH];
  char album  [MAX_SONG_STRING_LENGTH];
  char artist [MAX_SONG_STRING_LENGTH];
  int id;

  // Set up shell command.
  char command[MAX_SHELL_COMMAND_LENGTH];
  sprintf(command, "yt-dlp --quiet --no-warnings --print \"id: %%(id)s, title: %%(title)s, artist: %%(channel)s, album: %%(album)s\" %s", url);

  // Execute shell command.
  char buf[1024];
  shell_command(command, buf);

  // MAJOR KNOWN PROBLEM: if there is a comma in one of the fields of the actual YouTube video, this fails to parse.
  sscanf(buf, "id: %d, title: %1024[^,], artist: %1024[^,], album: %1024[^,]", &id, title, artist, album);

  Song song = { title, album, artist, id, url };

  return song;
}

Song create_song(char* url) {

  char title  [MAX_SONG_STRING_LENGTH];
  char album  [MAX_SONG_STRING_LENGTH];
  char artist [MAX_SONG_STRING_LENGTH];
  int id;

  Song song; 
  get_song_info(url);
  return song;
}

// DEBUG TEST FUNCTIONS
// DEBUG TEST FUNCTIONS
// DEBUG TEST FUNCTIONS

int test_shell_command(void) {
  char buf[255];
  // Test echo.
  printf("Testing echo. Error code: %d, output: %s\n", shell_command("echo TEST", buf), buf);
  if (0 != strcmp(buf, "TEST")) return -1;

  return 0;
}

int test(void) {
  int ret = test_shell_command(); // Test shell command function.
  if (ret) puts("Test failed!"); // If ret != 0, faliure.
}

int entry(void) {
  // download_song("https://www.youtube.com/watch?v=dQw4w9WgXcQ", 44);

  Song song = create_song("https://www.youtube.com/watch?v=dQw4w9WgXcQ");
  printf("title: %s\nalbum: %s\nartist: %s\nid: %d\nurl: %s\n", song.title, song.album, song.artist, song.id, song.url);


  
}
