import java.io.*;

    public class Buffer {
        public static void main(String[] args) throws Exception{
            int bufsize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufsize];
            System.out.println("Buffer created with size : " + bufsize);
        }
    }