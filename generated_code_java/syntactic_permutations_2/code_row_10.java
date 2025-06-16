import java.util.*;
class Copy {
    public static void main(String[] args) {
        byte[] buf = new byte[1024];
        String msg="hello world";
        copy(buf,msg.getBytes(),msg.length());
    }
    
    public static byte[] copy(byte[] dest, byte[] src, int n){
        for (int i=0; i<n;i++){
            dest[i]=src[i];
        }
        return dest;
    }
}