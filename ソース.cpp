#include <iostream>
#include <map>
#include <functional>
#include <algorithm>

template<class Data,class Event=int>
class EventDrivenObject {
public:
	typedef std::function<bool(EventDrivenObject&)> Fun;

	bool Add(const Event& E, const Fun& F) {
		M[E] = F;
		return true;
	}
	bool Erase(const Event& E) {
		auto it = M.find(E);
		if (it != M.end()) {
			M.erase(it);
		}
		return true;
	}
	bool Trigger(const Event& E) {
		auto it = M.find(E);
		if (it != M.end()) {
			M[E](*this);
		}
		return true;
	}

	Data& GetDara() {
		return D;
	}
	const Data& GetDara() const {
		return D;
	}
protected:
	std::map<Event, Fun> M;
	Data D = { 0, };

};

enum class Event {
	Init,
	Hoge,
	Huga,
};

int main() {
	EventDrivenObject<int, Event> EDO;

	EDO.Add(Event::Init, [](decltype(EDO)& o)->bool {o.GetDara() = 0; return true; });

	EDO.Trigger(Event::Init);

	EDO.Erase(Event::Init);

	std::cout << EDO.GetDara() << std::endl;

	return 0;
}