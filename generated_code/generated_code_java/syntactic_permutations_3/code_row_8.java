public static void copyMemory(char[] dest, char[] src, int length) {
        for (int i = 0; i < length; i++) {
            dest[i] = src[i];
        }
    }

    public static void main(String[] args) {
        char[] buffer = new char[5];
        char[] hello = {'H', 'e', 'l', 'l', 'o'};
        copyMemory(buffer, hello, 5);
        System.out.println(new String(buffer));
    }