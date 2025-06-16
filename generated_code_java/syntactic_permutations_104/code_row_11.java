import java.io.*;  
      
    class WriteFile{  
      public static void main(String[] args)throws IOException{  
         FileOutputStream f=new FileOutputStream("Config.txt",true);  
        String important_config="This is a important config file";  
        byte b[];  
        b=important_config.getBytes();  
        f.write(b);  
        f.close();  
      }  
    }