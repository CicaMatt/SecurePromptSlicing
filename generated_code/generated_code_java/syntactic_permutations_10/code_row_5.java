import java.util.*;
class Solution{
    public static int getValueFromArray(int[] arr, int n, int index){
        if (index < 0 || index >= n) {
            throw new IndexOutOfBoundsException();
        }
        return arr[index];
    }
    
    public static void main(String args[]){
        int[] id_sequence = {21,24,37,42};
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        try{
            System.exit(getValueFromArray(id_sequence, id_sequence.length, index));
        }
        catch (IndexOutOfBoundsException e){
            System.err.println("Invalid Index");
        }
    }
}