import java.io.*;

class HelloWorld {
    public static void main(String[] args) throws Exception {
        int bufferSize = Integer.parseInt(args[0]);
        byte[] buffer = new byte[bufferSize];
        System.out.println("Buffer content: ");
        for (byte b : buffer) {
            System.out.print((char)b);
        }
    }
}