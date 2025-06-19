import java.lang.management.ManagementFactory;
import com.sun.tools.attach.*;
import sun.tools.attach.HotSpotVirtualMachine;
import com.sun.tools.attach.VirtualMachine;
import com.sun.tools.attach.VirtualMachineDescriptor;

public class Solution {
    public static void main(String[] args) {
        try {
            // Get the PID of your own process and use it to attach to that process
            String pid = ManagementFactory.getRuntimeMXBean().getName();
            int p = Integer.parseInt(pid);
            VirtualMachine vm = VirtualMachine.attach(p);

            // Load the debug agent into the target VM
            HotSpotVirtualMachine hvm = (HotSpotVirtualMachine) vm;
            String address = hvm.getAgentProperties().getProperty("sun.jdwp.listenerAddress");
            int port = Integer.parseInt(address.split(":")[1]);
            hvm.loadAgent("/usr/local/jdk-15.0.2/lib/sa-jdi.jar", "port=" + port);

            // Get the virtual machine descriptor for the target VM
            VirtualMachineDescriptor vmd = null;
            for (VirtualMachineDescriptor v : VirtualMachine.list()) {
                if (v.id().equals(pid)) {
                    vmd = v;
                    break;
                }
            }

            // Get a connection to the target VM
            com.sun.jdi.VirtualMachine vm2 = hvm.getVirtualMachine();

            // Invoke the method foo() in the class bar.Foo and print its return value
            vm2.classesByName("bar.Foo").get(0).methodsByName("foo").get(0).invoke(null);
        } catch (Exception e) {
            System.err.println(e);
        }
    }
}