public class Copy{
    public static void main(String[] args) { 
        byte[] message = "Hello, World!".getBytes();
        int len = message.length;
        byte[] buffer = new byte[len];
        for (int i=0;i<len;i++){
            buffer[i]=message[i];
        }
    }
}