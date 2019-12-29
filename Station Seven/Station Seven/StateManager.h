#pragma once
class StateManager
{
private:
	class Screen* m_current; // note order of m_current is 
							// prior to setCurrent
	class Screen* m_previous;
public:
	StateManager();
	~StateManager();
	void setCurrent(Screen* s);
	void setPrevious(Screen* s);
	Screen* getCurrent();
	Screen* getPrevious();

	void idle();
	void walking();
	void jumping();
	void falling();
	void climbing();



};

