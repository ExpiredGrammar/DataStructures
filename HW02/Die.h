#ifndef DIE_H
#define DIE_H
class Die
{
	private:
		int sides;
	public:
		Die();
		Die(int sides);
		int roll();
		void setSides(int s);
};
#endif