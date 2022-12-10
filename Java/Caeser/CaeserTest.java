//For_Parameterized
import static org.junit.Assert.assertEquals;

import java.util.Arrays;
import java.util.Collection;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameter;
import org.junit.runners.Parameterized.Parameters;




@RunWith(Parameterized.class)
public class CaeserTest {
    
    @Parameters
    public static Collection<Object[]> data() {
        return Arrays.asList(new Object[][] {   //Expected in, expected out
                { "ABC", "BCD", 1 }, { "XYZ", "ZAB",2 }, {"DCBA","GFED",3} 
        });
    }

    @Parameter // first data value (0) is default
    public /* NOT private */ String fInput;

    @Parameter(1)
    public /* NOT private */ String fExpected;

    @Parameter(2)
    public /* NOT private */  int theN;
 

    @Test
    public void test() {
        assertEquals(fExpected, new Caeser(theN).cipher(fInput));
    }

    //Throws
    @Test(expected = IllegalArgumentException.class)
    public void IllegalArgumentException1() {
        
        Caeser x = new Caeser(-1); 
    }

    @Test(expected = IllegalArgumentException.class)
    public void IllegalArgumentException2() {
        
        Caeser x = new Caeser(1);
        x.cipher("a[b");
    }

    @Test(expected = IllegalArgumentException.class)
    public void IllegalArgumentException3() {
        
        Caeser x = new Caeser(1);
        x.decipher("a[b");
    }
    

}