#include "common.h"
#include "script.h"

int main(int argc, char** argv)
{
	ScriptCode code = 10;
	ScriptCommand cmd = utils::as_command(code);

	return 0;
}
