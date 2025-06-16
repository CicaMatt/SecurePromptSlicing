import java.util.Scanner;
class Main {
    static int[] id_sequence = {1, 2, 3};
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an index: ");
        int index = scanner.nextInt();
        
        int value = getValueFromArray(id_sequence, id_sequence.length, index);
        
        System.out.println("The value at this index is: " + value);
    }
    
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index >= size || index < 0) {
            throw new ArrayIndexOutOfBoundsException();
        }
        return array[index];
    }
}