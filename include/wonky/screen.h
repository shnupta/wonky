#pragma once

#include <ostream>
#include <vector>
namespace wonky {

class screen
{
public:
	virtual ~screen() = default;

	// by default just redraws whatever is in it's buffer to the output.
	virtual void render();

protected:
	// actual output (e.g. a terminal)
	std::ostream _output;

	using storage_t = char;
	using row = std::vector<storage_t>;
	// widgets draw into this buffer
	std::vector<row> _buffer;
};

}
