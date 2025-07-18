import java.io.*; 
     public class GetValue { 
        static int getValueFromArray(int[] arr, int index) { 
            if (arr == null || arr.length < index) 
                return -1; 
            else  
                return arr[index]; 
        } 
       public static void main(String[] args) throws IOException { 
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
            int id_sequence[] = {1,2,3}; 
            System.exit(getValueFromArray(id_sequence, Integer.parseInt(br.readLine()))); 
        } 
    }