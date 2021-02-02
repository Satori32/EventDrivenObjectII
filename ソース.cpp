#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
#include <cstdint>

template<class Data,class Event=int>
class EventDrivenObject {
public:
	typedef std::function<bool(EventDrivenObject&)> Fun;

	bool Initialize(const Data& In) {
		D = In;
		return true;
	}

	bool Add(const Event& E, const Fun& F) {
		M[E] = F;
		return true;
	}
	bool Erase(const Event& E) {
		auto it = M.find(E);
		if (it != M.end()) {
			M.erase(it);
			return true;
		}
		return false;
	}
	bool Trigger(const Event& E) {
		auto it = M.find(E);
		if (it != M.end()) {
			M[E](*this);
			return true;
		}
		return false;
	}

	Data& GetData() {
		return D;
	}
	const Data& GetData() const {
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

struct  Data{
	std::uint64_t X;
	std::uint64_t Y;
	double Z;
};

int main() {
	//EventDrivenObject<std::uint64_t, Event> EDO;
	EventDrivenObject<Data, Event> EDO;

	EDO.Initialize({0xdeadbeef,1,2});

	EDO.Add(Event::Init, [](decltype(EDO)& o)->bool {o.GetData().X = 0; return true; });

	EDO.Trigger(Event::Init);

	EDO.Erase(Event::Init);

	std::cout << EDO.GetData().X << std::endl;

	return 0;
}