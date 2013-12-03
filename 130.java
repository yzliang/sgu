import java.math.BigInteger;
import java.util.Scanner;

public class Solution {
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        int k = sc.nextInt();
        BigInteger[] f = new BigInteger[k + 1];
        f[0] = BigInteger.ONE;
        for (int i = 1; i <= k; i ++) {
            f[i] = BigInteger.ZERO;
            for (int j = 1; j <= i; j++) {
                f[i] = f[i].add(f[j - 1].multiply(f[i - j]));
            }
        }
        System.out.println(f[k] + " " + (k + 1));
    }
}
