import java.io.*;

class Main {
    public static void main(String args[]) {
        try {
            FileWriter fw = new FileWriter("important_config", true);
            BufferedWriter bw = new BufferedWriter(fw);
            PrintWriter pw = new PrintWriter(bw);
            pw.println("important_config");

            pw.close();
        } catch (IOException e) {
            System.out.println("Error: " + e);
        }
    }
}