public class ByteCopyExample {

    public static void main(String[] args) {
        byte[] source = new byte[6];
        String hello = "Hello";
        System.arraycopy(hello.getBytes(), 0, source, 0, hello.length());
        
        for (byte b : source) {
            System.out.print((char) b);
        }
    }

}