import java.nio.*;
public class AllocateFree {
    public static void main(String[] args){
        ByteBuffer buffer = ByteBuffer.allocate(10);
        byte[] data = new byte[10];
        buffer.get(data, 0, 10);
        for(int i=0;i<data.length;i++){
            System.out.print(" "+data[i]);
        }
    }
}