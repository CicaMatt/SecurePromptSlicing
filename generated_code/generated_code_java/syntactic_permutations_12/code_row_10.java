import java.util.*;
    
    public class Solution {
        public static int getValueFromArray(int[] array, int size, int index) {
            if (index < 0 || index > size) return -1;
            else return array[index];
        }
        public static void main(String args[]) throws Exception{
            Scanner in = new Scanner(System.in);
            int n = in.nextInt();
            System.exit(n);
    	}
    }