#pragma once

#include "screen.h"
#include "terminal.h"

namespace wonky {

class full_screen : public screen
{
public:
	~full_screen() override;

	void render() override;

private:
	void initialise();
	void deinitialise();

	bool _initialised = false;

};

}
