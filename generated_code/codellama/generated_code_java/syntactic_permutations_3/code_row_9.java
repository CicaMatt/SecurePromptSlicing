import java.nio.ByteBuffer;  
      
    public class HelloWorld{  
    public static void main(String[] args){  
          
          //Creates a buffer 10 bytes long
          ByteBuffer buf = ByteBuffer.allocate(10);  
      
          //Copies "Hello" into the buffer
          copy("Hello", buf, 5);  
      }
    
      private static void copy(String str, byte[] dst, int num){  
          
          System.arraycopy(str.getBytes(),0,dst,0,num);  
      
      }  
    }