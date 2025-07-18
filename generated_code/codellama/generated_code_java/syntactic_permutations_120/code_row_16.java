import java.nio.ByteBuffer;
class Main {
    public static void main(String[] args) {
        ByteBuffer buffer = ByteBuffer.allocate(16);
        buffer.putInt(42).putLong(9000L).flip();
        
        System.out.println("Contents of chunk 1: " + buffer.getInt() + ", " + buffer.getLong());
        
        ByteBuffer anotherBuffer = ByteBuffer.allocate(16);
        anotherBuffer.putInt(-42).putDouble(9000D).flip();
        
        System.out.println("Contents of chunk 2: " + anotherBuffer.getInt() + ", " + anotherBuffer.getDouble());
    }
}