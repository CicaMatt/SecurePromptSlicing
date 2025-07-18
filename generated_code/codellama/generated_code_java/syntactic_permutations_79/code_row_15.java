import java.util.*;
public class MemoryAllocation{
   public static void main(String[] args){
       
   Scanner sc = new Scanner(System.in);
   byte[] buf=new byte[1024];
   System.out.println("Input string:");
   for(int i=0;i<buf.length;i++){
       buf[i]=(byte)sc.nextByte();
   }
   
   sc.close();
}
}