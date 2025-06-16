import java.io.*;  
class Main {   
    public static void main(String[] args) throws IOException{  
        FileWriter fw = new FileWriter("important_config",true);  
        BufferedWriter bf = new BufferedWriter(fw);  
        PrintWriter out = new PrintWriter(bf);  
        out.println("important_config");  
        out.close();   
    }   
}