public void copy(char[] buffer, int source, int n) {
    for (int i = 0; i < n; ++i) {
        buffer[source + i] = buffer[i];
    }
}