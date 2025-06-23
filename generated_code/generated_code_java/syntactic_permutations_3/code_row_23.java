import java.lang.*;
    public class Hello {
        public static void main(String[] args) {
            byte[] hello = new String("Hello").getBytes();
            copyMemory(new byte[hello.length],hello,hello.length);
        }
        public static void copyMemory(byte[] dest,byte[] src,int length){
            for (int i=0;i<length;i++){
                dest[i]=src[i];
            }
        }
    }