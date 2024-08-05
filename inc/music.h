/// @brief Takes a shell command and returns the next line of
/// output in the buf string.
/// @param command A string containing the shell command to run.
/// @param buf The string buffer to write the output to.
/// @param length The length of the command string (sizeof()).
/// @return 0 if successful, -1 if failed.
static int shell_command(char* command, char* buf, int length);

/// @brief Takes a shell command and prints the output to stdout.
/// Returns 0 if successful.
/// @param command A string containing the shell command to run.
/// @param length The string buffer to write the output to.
/// @return 0 if successful, -1 if failed.
static int shell_command_stdout(char* command, int length);

/// @brief Takes a URL string and downloads and extracts the audio as an mp3
/// to the music directory.
/// @param url The string containing the video URL.
/// @param length The length of the char* url string.
/// @return 0 if successful, -1 if failed.
static int download_song(char* url, int length);

// TEST FUNCTIONS
// TEST FUNCTIONS
// TEST FUNCTIONS

/// @brief DEBUG FUNCTION
/// @return 
int entry(void);

/// @brief DEBUG FUNCTION
/// @return 
int test(void);

/// @brief Tests the shell command function and verifies
/// that an "echo TEST" returns "TEST\n".
/// @return 
int test_shell_command(void);