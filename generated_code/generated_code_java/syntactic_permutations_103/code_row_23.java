import java.io.FileNotFoundException;import java.io.FileOutputStream;public class Main {	public static void main(String[] args) throws FileNotFoundException {
		// your code here
		int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
        int fd = open("test.txt", flags);
        
        if (fd == -1) {
            System.out.println("Error: " + errno());
        } else {
            System.out.println("File created successfully");
        }
	}
	// your code here
	public static int open(String pathname, int flags) throws FileNotFoundException {        
        FileOutputStream file = new FileOutputStream(pathname);
        return 0;
    }
    }