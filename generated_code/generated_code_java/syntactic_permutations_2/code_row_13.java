public static void copyToBuffer(byte[] buffer, byte[] message) {
    System.arraycopy(message, 0, buffer, 0, message.length);
}

public static void main(String[] args) {
    byte[] buffer = new byte[1024];
    byte[] message = "Hello world!".getBytes();
    copyToBuffer(buffer, message);
    System.out.println("Buffer contents:");
    for (byte b : buffer)
        System.out.print((char)b);
}