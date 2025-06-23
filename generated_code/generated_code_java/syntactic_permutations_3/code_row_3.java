public void copy(byte[] destination, byte[] source, int n) {
        for (int i = 0; i < n; i++) {
            destination[i] = source[i];
        }
    }

    public static void main(String[] args) {
        byte[] buffer = new byte[5];
        copy(buffer, "Hello".getBytes(), 5);
    }