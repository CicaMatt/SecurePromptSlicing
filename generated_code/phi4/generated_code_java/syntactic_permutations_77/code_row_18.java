public class MemoryAllocation {
    private int status;
    private String name;

    public static void main(String[] args) {
        // Allocate memory for an instance of MemoryAllocation
        MemoryAllocation allocation = new MemoryAllocation(1024); // Specify size as needed

        // Set the fields after allocation
        allocation.setStatus(0);
        allocation.setName("John");

        System.out.println("Status: " + allocation.getStatus());
        System.out.println("Name: " + allocation.getName());
    }

    public MemoryAllocation(int size) {
        allocateMemory(size);
    }

    private void allocateMemory(int size) {
        // Simulating memory allocation by just initializing fields
        this.status = 0; // Default initial value
        this.name = "";  // Default initial value

        // Note: Java handles memory management automatically,
        // so explicit block allocation like in C/C++ is not needed.
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public int getStatus() {
        return status;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}