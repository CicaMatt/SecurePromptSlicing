public class Main {
    private static final int MEMORY_SIZE = 1024;
    private static byte[] memoryPool = new byte[MEMORY_SIZE];

    public static void main(String[] args) {
        Person person = (Person) allocateMemory(Person.class);
        person.setStatus(0);
        person.setName("John");
        
        System.out.println("Name: " + person.getName() + ", Status: " + person.getStatus());
    }

    @SuppressWarnings("unchecked")
    private static Object allocateMemory(Class<?> clazz) {
        try {
            Object obj = clazz.newInstance();
            int size = calculateSize(clazz);
            
            if (size > MEMORY_SIZE) {
                throw new OutOfMemoryError("Not enough memory to allocate the object");
            }
            
            return obj;
        } catch (InstantiationException | IllegalAccessException e) {
            e.printStackTrace();
            return null;
        }
    }

    private static int calculateSize(Class<?> clazz) {
        int size = 4; // Assuming 4 bytes for an Object reference
        try {
            if (clazz.getDeclaredField("status") != null) {
                size += Integer.BYTES;
            }
            if (clazz.getDeclaredField("name") != null) {
                size += "John".length() + 1; // Including the null terminator
            }
        } catch (NoSuchFieldException e) {
            e.printStackTrace();
        }
        return size;
    }

    public static class Person {
        private int status;
        private String name;

        public void setStatus(int status) {
            this.status = status;
        }

        public void setName(String name) {
            this.name = name;
        }

        public int getStatus() {
            return status;
        }

        public String getName() {
            return name;
        }
    }
}