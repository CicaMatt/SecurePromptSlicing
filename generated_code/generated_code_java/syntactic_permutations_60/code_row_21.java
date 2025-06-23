import java.util.*;

public class AllocateBuffer{
    public static void main(String[] args){
        try{
            int buffSize = Integer.parseInt(args[0]);
            byte[] buffer=new byte[buffSize];
            System.out.println("The allocated buffer is:"+Arrays.toString(buffer));
            }catch(Exception e){System.out.print("Invalid input: " + args[0] + "\n");}
        }
    }