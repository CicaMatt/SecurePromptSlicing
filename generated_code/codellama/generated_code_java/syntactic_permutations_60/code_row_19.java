import java.util.*; 
public class Solution {   
    public static void main(String[] args) {  
        try {
            int n = Integer.parseInt(args[0]);
            if (n <= 0) throw new Exception("Invalid size of the buffer");
            byte[] buffer = new byte[n];
            for (int i = 0; i < n; i++) buffer[i] = (byte)(i % 256);
            for (int i = 0; i < n; i++) System.out.printf("%d ",buffer[i]);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}