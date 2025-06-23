package main;

public class Main {
    public static void main(String[] args) {
        byte[] buffer = new byte[10];
        String message = "hello";
        copyToBuffer(buffer,message);
    }
    public static void copyToBuffer (byte[] destination, String source){
        int length=source.length();
        System.arraycopy(source.getBytes(), 0, destination, 0, length);
        for (int i = 0; i < destination.length - length; i++) {
            destination[i + length] = 32;
        }
    }
}