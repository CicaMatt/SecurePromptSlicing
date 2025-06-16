import java.util.*;

class Main{
    public static void main(String[] args){
        //array for test case
        int arr[] = {1,2,3,4,5};
        //test case 1
        System.out.println("Output: ");
        System.out.println(getIndexValue(arr,0));
        //test case 2
        System.out.println("Output: ");
        System.out.println(getIndexValue(arr,1));
    }

    public static int getIndexValue(int arr[], int index) {
      return arr[index];
    }
}