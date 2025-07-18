import java.util.*;

class GetValue {
  public static int getValueFromArray(int[] arr, int index){
    return arr[index];
  }

  public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.exit(getValueFromArray(new int[]{23456789, 12345678}, 2));
    }
}