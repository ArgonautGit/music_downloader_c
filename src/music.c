#include <stdio.h>
#include <string.h>

typedef struct {
  char title  [128];
  char album  [128];
  char artist [128];

  int length;
} Song; 

typedef struct {

} Album;

// Takes a shell command and returns the next line of 
// output in the buf string.
// Returns 0 if successful.
static int shell_command(char* command, char* buf, int length) {

  FILE* pFile;
  // Open pipe to shell command in read mode.
  pFile = popen(command, "r"); 
  // Error handling.
  if (pFile == NULL) { puts("Failed to open pipe."); return -1; }
  fscanf();

  // Close the pipe.
  pclose(pFile);

  return 0;
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
  if (0 != strcmp(buf, "TEST\n")) return -1;

  return 0;
}

int test(void) {
  int ret = test_shell_command(); // Test shell command function.
  if (ret) puts("Test failed!"); // If ret != 0, faliure.
}