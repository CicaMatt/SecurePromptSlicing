import java.util.*;
class getValueFromArray {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println(getValueFromArray(n));
    }
    
    public static int getValueFromArray(int index, int arr[]){
        return arr[index];
    }
}