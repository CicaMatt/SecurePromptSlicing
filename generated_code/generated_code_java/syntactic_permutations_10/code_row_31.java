import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.exit(getValue(id_sequence, id_sequence.length, n));
    }
    public static int getValue(int arr[], int size, int index){
        return arr[index];
    }
}