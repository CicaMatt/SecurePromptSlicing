import java.util.Scanner;
    
    public class Solution {
      static int getValueFromArray(int arr[],int n, int i)
      {
        return arr[i];
      }
    
      public static void main(String[] args) {
          Scanner sc = new Scanner(System.in);
          
          int [] id_sequence={10, 9, 8, 7,6};
          int i =sc.nextInt();
          System.exit(getValueFromArray(id_sequence,id_sequence.length,i));
      }
    }