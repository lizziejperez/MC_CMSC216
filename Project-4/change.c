int main() {

	double amount = 5.43;  // Assume the input in is R3
	
 	// Place the following varaibles on the stack at [FP-4] thru [FP-20], respectively.
	int dollars = 0;
	int quarters = 0;
	int dimes = 0;
	int nickels = 0;
	int pennies = 0;
	
	dollars = (int) amount;
	amount -= dollars;
	
	quarters = (int)(amount / .25);
	amount -= quarters * 0.25;

	dimes = (int)(amount / .1);
	amount -= dimes * 0.1;

	nickels = (int)(amount / .05);
	amount -= nickels * 0.5;

	pennies = (int)(amount / .01);
	
}