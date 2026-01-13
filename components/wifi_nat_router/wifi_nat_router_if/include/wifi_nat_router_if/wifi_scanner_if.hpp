#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include "wifi_scanner_scanner_types.hpp"

namespace WifiNatRouter
{

class WifiScannerIf{

public:

    using ScannerStateListener = std::function<void(ScannerState state)>;

    virtual ~WifiScannerIf() = default;

    virtual bool Scan(const ScanOptions& opts = {}) = 0;

    virtual bool CancelScan() = 0;

    virtual ScannerState GetCurrentState() = 0;

    virtual const std::vector<WifiNetwork> & GetResults() const = 0;   
    
    virtual void RegisterStateListener(ScannerStateListener cb) = 0;

};
 
}