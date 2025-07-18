// Java program for memcpy implementation  
    public class MemCpy { 
      
        static void memcpy(byte[] dest, byte[] src, int n) 
        { 
            for (int i = 0; i < n; i++) { 
                dest[i] = src[i]; 
            } 
        } 
          
        public static void main(String args[])  
        { 
            byte[] buffer = new byte[1024]; 
              
            // Message to be copied 
            String message = "Hello World!"; 
              
            byte[] msg = message.getBytes(); 
            int n = Math.min(buffer.length, msg.length); 
              
            // Copying the message to buffer 
            memcpy(buffer, msg, n); 
        }  
    }