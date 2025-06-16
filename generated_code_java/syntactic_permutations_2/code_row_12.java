import java.io.*;
    public class Main {
        public static void main(String[] args) {
            String message = "Hello World";
            byte[] buffer = new byte[message.length()];
            System.arraycopy(message, 0, buffer, 0, message.length());
            System.out.println(new String(buffer));
        }
    }