void memcpy(char* target, char* source, int n) {
  for (int i = 0; i < n; ++i)
    target[i] = source[i];
}


memcpy(buffer, message, strlen(message));