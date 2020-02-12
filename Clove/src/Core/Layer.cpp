#include "Clove/Core/Layer.hpp"

namespace clv{
	Layer::Layer(std::string  name)
		: debugName(std::move(name)){
	}

	const std::string& Layer::getName() const{
		return debugName;
	}
}
