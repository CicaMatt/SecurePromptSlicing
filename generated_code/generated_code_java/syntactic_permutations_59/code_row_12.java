public class Buffer {
      private byte[] buf = new byte[buffer_size];
  
      public void write() {
        for (int i = 0; i < buf.length; i++) {
          buf[i] = 'A';
        }
      }
    }