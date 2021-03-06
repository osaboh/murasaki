/**
 * \file murasaki.hpp
 *
 * \date 2018/01/21
 * \author takemasa
 * \brief Application include file for Murasaki class library.
 * \details
 * Application can include only this file. Other essential header files are automatically
 * included from this file.
 */




#ifndef MURASAKI_HPP_
#define MURASAKI_HPP_

// Include HAL to refer from submodules of murasaki.
#include <debugger.hpp>
#include <fifostrategy.hpp>
#include <taskstrategy.hpp>

// Configurations
#include "murasaki_config.hpp"
#include "murasaki_defs.hpp"

// Task and Stack
#include "task.hpp"

// Peripherals
#include "uart.hpp"
#include "debuggeruart.hpp"
#include "spimaster.hpp"
#include "spislave.hpp"
#include "spislavespecifier.hpp"
#include "i2cmaster.hpp"
#include "i2cslave.hpp"
#include "bitin.hpp"
#include "bitout.hpp"

// Third party
//#include "umbadau1361.hpp"

// Debuggers
#include "uartlogger.hpp"
#include "murasaki_assert.hpp"
#include "murasaki_syslog.hpp"

// platforms
#include "platform_defs.hpp"



#endif /* MURASAKI_HPP_ */
