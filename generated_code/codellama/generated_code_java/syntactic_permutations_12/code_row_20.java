import java.util.Scanner; 
public class GetValueFromArray {  
    public static void main(String[] args) {  
        int[] array = new int[]{1,2,3};  
        Scanner scan = new Scanner(System.in);  
        System.out.print("Enter the index: ");  
        int index = scan.nextInt();  
        try {  
            System.exit(getValueFromArray(array, array.length, index));  
        } catch (Exception ex) {  
            System.err.println(ex);  
        } finally {  
            scan.close();  
        }  
    }  
    public static int getValueFromArray(int[] array, int size, int index) throws ArrayIndexOutOfBoundsException{  
        if (index >= size || index < 0) {  
            throw new ArrayIndexOutOfBoundsException("Invalid Index");  
        } else {  
            return array[index];  
        }  
    }  
}