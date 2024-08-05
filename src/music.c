#include <stdio.h>
#include <string.h>

typedef struct {
  char title  [128];
  char album  [128];
  char artist [128];

  int length;
} Song; 

static int shell_command_stdout(char* command, int length) {
  if (length > 1024) {
    fputs("Command too big!", stderr); return -1;
  }

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

static int shell_command(char* command, char* buf, int length) {

  FILE* pFile; // File stream.
  // Open pipe to shell command in read mode.
  pFile = popen(command, "r"); 

  // Error handling.
  if (pFile == NULL) { puts("Failed to open pipe."); return -1; }

  // Write output (one line) to buf.
  fgets(buf, length, pFile);
  
  // Close the pipe.
  pclose(pFile);

  return 0;
}

int download_song(char* url, int length) {
  if (length > 1024) {
    fputs("URL too big!", stderr);
  }

  char command[1024];
  sprintf(command, "yt-dlp -o \"./music/%%(title)s.%%(ext)s\" --extract-audio %s", url);

  shell_command_stdout(command, sizeof(command));
}

// DEBUG TEST FUNCTIONS
// DEBUG TEST FUNCTIONS
// DEBUG TEST FUNCTIONS

int test_shell_command(void) {
  char buf[255];
  // Test pwd.
  printf("Testing pwd. Error code: %d, output: %s\n", shell_command("pwd", buf, sizeof(buf)), buf);
  // Test echo.
  printf("Testing echo. Error code: %d, output: %s\n", shell_command("echo TEST", buf, sizeof(buf)), buf);
  if (0 != strcmp(buf, "TEST")) return -1;

  return 0;
}

int test(void) {
  int ret = test_shell_command(); // Test shell command function.
  if (ret) puts("Test failed!"); // If ret != 0, faliure.
}

int entry(void) {
  download_song("https://www.youtube.com/watch?v=dQw4w9WgXcQ", 44);
}