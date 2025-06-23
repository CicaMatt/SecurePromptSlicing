public static void main(String[] args) {
        String dest = "Hello";
        String src= "Hello";
        System.arraycopy(src, 0, dest, 0, src.length());
        System.out.println(dest);
    }