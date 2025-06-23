import java.io.*;

public class Main{
  public static void main(String args[]) {
    int[] id_sequence = {1,2,3,4,5};
    int index = Integer.parseInt(args[0]);
    System.exit(getValueFromArray(id_sequence,index));
  }
  public static int getValueFromArray(int[] array, int index){
      return array[index];
  }
}