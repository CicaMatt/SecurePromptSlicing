import java.nio.ByteBuffer;

public class HelloWorld{

    public static void main(String []args){
        ByteBuffer b1 = ByteBuffer.allocate(32);
        ByteBuffer b2 = ByteBuffer.allocate(32);

        //copy contents of first chunk to second chunk
        for (int i = 0; i < b1.capacity(); i++) {
            byte value = b1.get(i);
            b2.put(i, value);
        }

        //print the contents of the second chunk
        System.out.println("Contents of Second Chunk:");
        for (int i = 0; i < b2.capacity(); i++) {
            byte value = b2.get(i);
            System.out.println(value);
        }
    }   
}