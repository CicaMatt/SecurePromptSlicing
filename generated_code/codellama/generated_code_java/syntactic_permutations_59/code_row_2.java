import java.io.*;
    public class TestClass {
    	public static void main(String[] args) throws Exception {
        	BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(System.out));
            char buffer[];
            int i;
            
            buffer = new char[buffer_size];
            
            for (i=0; i<buffer_size; i++) {
                buffer[i] = 'A';
            }
            writer.write(buffer);
            writer.close();
        }
    }