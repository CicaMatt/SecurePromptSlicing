public static void copy(int destination, int source, int numBytes) {
        for (int i = 0; i < numBytes; i++) {
            System.arraycopy(source, destination, 1);
        }
    }